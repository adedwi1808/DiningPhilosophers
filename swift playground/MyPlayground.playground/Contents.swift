import Foundation

actor DiningPhilosophers {
    enum State {
        case thinking, hungry, eating
    }

    private var states: [State] = Array(repeating: .thinking, count: 5)
    private var waitingContinuations: [Int: CheckedContinuation<Void, Never>] = [:]

    func takeForks(id: Int) async {
        states[id] = .hungry
        await tryEatOrWait(id: id)
    }

    func putForks(id: Int) {
        states[id] = .thinking
        print("💭 Philosopher \(id) is thinking")

        let left = (id + 4) % 5
        let right = (id + 1) % 5

        if let cont = waitingContinuations[left], canEat(id: left) {
            waitingContinuations[left] = nil
            states[left] = .eating
            cont.resume()
        }

        if let cont = waitingContinuations[right], canEat(id: right) {
            waitingContinuations[right] = nil
            states[right] = .eating
            cont.resume()
        }
    }

    private func tryEatOrWait(id: Int) async {
        if canEat(id: id) {
            states[id] = .eating
            print("🍝 Philosopher \(id) is eating")
        } else {
            await withCheckedContinuation { (continuation: CheckedContinuation<Void, Never>) in
                waitingContinuations[id] = continuation
            }
            print("🍝 Philosopher \(id) resumes and starts eating")
        }
    }

    private func canEat(id: Int) -> Bool {
        let left = (id + 4) % 5
        let right = (id + 1) % 5
        return states[left] != .eating && states[right] != .eating
    }
}

func philosopher(id: Int, table: DiningPhilosophers) async {
    while true {
        print("💬 Philosopher \(id) is thinking...")
        try? await Task.sleep(nanoseconds: UInt64.random(in: 500_000_000...1_000_000_000))
        
        await table.takeForks(id: id)
        try? await Task.sleep(nanoseconds: UInt64.random(in: 500_000_000...1_000_000_000)) // makan
        
        await table.putForks(id: id)
    }
}

func main() async {
    let table = DiningPhilosophers()
    
    for id in 0..<5 {
        Task.detached {
            await philosopher(id: id, table: table)
        }
    }
    
    // Biarkan simulasi jalan terus
    try? await Task.sleep(nanoseconds: 10_000_000_000)
    print("🔚 Simulasi selesai.")
}

Task {
    await main()
}
